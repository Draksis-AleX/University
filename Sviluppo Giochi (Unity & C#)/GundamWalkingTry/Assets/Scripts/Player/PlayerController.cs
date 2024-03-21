using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;

[RequireComponent(typeof(CharacterController))]

public class PlayerController : MonoBehaviour
{
    // ======================================  MOVEMENT  ===================================================
    
    private CharacterController _characterController;
    private Vector2 _input, mouseLook;
    private Vector3 _direction;
    private Vector3 skewedInput;
    [SerializeField] float speed;
    [SerializeField] float default_speed;

    // ======================================  ROTATION  ===================================================

    private Vector3 rotationTarget;
    [SerializeField] private float smoothTime = 0.05f;
    private float _currentVelocity;

    // ======================================  GRAVITY  ===================================================

    private float _gravity = -9.81f;
    [SerializeField] private float gravityMultiplier = 3.0f;
    private float _velocity;

    // ======================================  ANIMATION  ===================================================

    private Animator _animator;
    private Vector3 motion;

    // ======================================  AIMING  ===================================================

    [SerializeField] Transform aimScope;
    LineRenderer aimLine;

    // ======================================  DEFAULT METHODS  ===================================================

    private void Start()
    {
        SetupAimingLine();
        speed = default_speed;
        SceneManager.activeSceneChanged += ChangedActiveScene;
    }

    void ChangedActiveScene(Scene current, Scene next)
    {
        ResetAiming();
        ResetSpeed();
    }

    private void Awake()
    {
        _characterController = GetComponent<CharacterController>();
        _animator = GetComponent<Animator>();
    }

    private void Update()
    {
        ApplyGravity();
        ApplyMovement();

        if(this.GetComponent<PlayerInput>().actions["Aiming"].WasPressedThisFrame())
        {
            //Debug.Log("Lower Speed");
            speed = default_speed * 0.5f;
            _animator.speed = 0.5f;
        }

        if (this.GetComponent<PlayerInput>().actions["Aiming"].WasReleasedThisFrame())
        {
            //Debug.Log("Reset Speed and Aiming");
            ResetAiming();
            ResetSpeed();
        }

        if (this.GetComponent<PlayerInput>().actions["Aiming"].IsPressed())
        {
            ApplyMouseRotation();
        }
        else
        {
            ApplyRotation();
        }
        
    }

    // ======================================  MOVEMENT  ===================================================

    public void CheckCommands()
    {
        if (GameManager.Instance.gameData.CommandsArrow == true) PlayerManager.Instance.GetComponent<PlayerInput>().SwitchCurrentActionMap("Gameplay #2");
        else PlayerManager.Instance.GetComponent<PlayerInput>().SwitchCurrentActionMap("Gameplay");
    }

    public void ResetSpeed()
    {
        speed = default_speed;
        _animator.speed = 1f;
    }

    public void Move(InputAction.CallbackContext context)
    {
        _input = context.ReadValue<Vector2>();
        var matrix = Matrix4x4.Rotate(Quaternion.Euler(0, 45, 0));

        _direction = new Vector3(_input.x, 0.0f, _input.y);
        skewedInput = matrix.MultiplyPoint3x4(_direction);
    }

    private void ApplyMovement()
    {
        motion = skewedInput * speed;
        //Debug.Log("Motion: " + motion.magnitude);
        _characterController.Move(motion * Time.deltaTime);
        _animator.SetFloat("Speed", motion.magnitude - speed);
    }

    public void increaseDefaultSpeed(float percentage)
    {
        default_speed = default_speed + (float)(default_speed * (float) percentage);
        //Debug.Log("Increased default_speed to " + default_speed);
        speed = default_speed;
    }

    // ======================================  GRAVITY  ===================================================

    private void ApplyGravity()
    {
        if (_characterController.isGrounded && _velocity < 0.0f)
        {
            _velocity = -1.0f;
        }
        else
        {
            _velocity += _gravity * gravityMultiplier * Time.deltaTime;
        }

        skewedInput.y = _velocity;
    }

    // ======================================  ROTATION  ===================================================

    public void mouseRotate(InputAction.CallbackContext context)
    {

        mouseLook = context.ReadValue<Vector2>();

    }

    private void ApplyRotation()
    {   
        if (_input.sqrMagnitude == 0) return;

        var targetAngle = Mathf.Atan2(skewedInput.x, skewedInput.z) * Mathf.Rad2Deg;
        var angle = Mathf.SmoothDampAngle(transform.eulerAngles.y, targetAngle, ref _currentVelocity, smoothTime);
        transform.rotation = Quaternion.Euler(0.0f, angle, 0.0f);
    }

    private void ApplyMouseRotation()
    {
        DrawAimingLine();

        int layerMask = 1 << 10;
        RaycastHit hit;
        Ray ray = Camera.main.ScreenPointToRay(mouseLook);
        if (Physics.Raycast(ray, out hit, Mathf.Infinity, layerMask))
        {
            rotationTarget = hit.point;
            Debug.DrawLine(ray.origin, hit.point);
        }

        Vector3 lookPos = rotationTarget - transform.position;
        lookPos.y = 0;
        var rotation = Quaternion.LookRotation(lookPos);

        Vector3 aimDirection = new Vector3(rotationTarget.x, 0f, rotationTarget.z);

        if (aimDirection != Vector3.zero)
        {
            transform.rotation = Quaternion.Slerp(transform.rotation, rotation, 0.15f);
        }
    }

    // ======================================  AIMING  ===================================================

    void SetupAimingLine()
    {
        aimLine = gameObject.GetComponent<LineRenderer>();
        aimLine.positionCount = 2;
    }

    void DrawAimingLine()
    {
        int layerMask = 1 << 9 | 1 << 7;
        RaycastHit aimHit;
        if (Physics.Raycast(aimScope.position, transform.TransformDirection(Vector3.forward), out aimHit, Mathf.Infinity, layerMask))
        {
            Debug.DrawLine(aimScope.position, aimHit.point);

            var points = new Vector3[2];
            points[0] = aimScope.position;
            points[1] = aimHit.point;
            aimLine.SetPositions(points);
        }
    }

    public void setAimingLineStatus(bool status)
    {
        this.gameObject.GetComponent<LineRenderer>().enabled = status;
    }

    public void ResetAiming()
    {
        var points = new Vector3[2];
        points[0] = Vector3.zero;
        points[1] = Vector3.zero;
        aimLine.SetPositions(points);
    }
}
