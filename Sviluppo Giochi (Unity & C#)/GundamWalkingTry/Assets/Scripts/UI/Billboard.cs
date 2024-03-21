using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Billboard : MonoBehaviour
{

    [SerializeField] Transform mainCamera;

    private void Start()
    {
        mainCamera = CameraManager.Instance.transform;
    }

    private void LateUpdate()
    {
        transform.LookAt(transform.position + mainCamera.forward);
    }

}
