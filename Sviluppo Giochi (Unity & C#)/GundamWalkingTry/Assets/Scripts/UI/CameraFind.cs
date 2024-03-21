using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CameraFind : MonoBehaviour
{

    [SerializeField] Canvas canvas;

    void Start()
    {
        findCamera();
    }

    private void OnEnable()
    {
        //findCamera();
    }

    public void findCamera()
    {
        canvas.worldCamera = CameraManager.Instance.GetComponent<Camera>();
    }
}
