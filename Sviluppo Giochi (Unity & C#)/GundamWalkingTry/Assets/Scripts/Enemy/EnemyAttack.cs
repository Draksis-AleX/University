using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.VFX;

public class EnemyAttack : MonoBehaviour
{
    [SerializeField] VisualEffect slashVFX;
    [SerializeField] float hitDistance = 6;
    [SerializeField] float coolDownTime = 1f;
    [SerializeField] int damage = 50;
    bool canAttack = true;
    Transform playerPosition;

    private void Start()
    {
        playerPosition = PlayerManager.Instance.transform;
    }

    private void Update()
    {
        if((Vector3.Distance(playerPosition.position, transform.position) < hitDistance) && canAttack)
        {
            canAttack = false;
            AudioMenager.Instance.PlayEffect("EnemySword");
            slashVFX.Play();
            this.gameObject.transform.LookAt(PlayerManager.Instance.transform);
            StartCoroutine(checkHit(slashVFX.GetFloat("duration")));
            StartCoroutine(coolDown());
        }
    }

    public IEnumerator coolDown()
    {
        yield return new WaitForSeconds(coolDownTime);
        canAttack = true;
    }

    public IEnumerator checkHit(float VFXDuration)
    {
        yield return new WaitForSeconds(VFXDuration / 2);
        bool hitted = transform.GetComponentInChildren<EnemyHitCheck>().checkHit();
        if (hitted)
        {
            PlayerManager.Instance.GetComponent<PlayerShieldManager>().takeDamage(damage);
        }
        yield return new WaitForSeconds(VFXDuration / 2);
        GetComponent<EnemySimpleMovement>().triggered = true;
    }

}
