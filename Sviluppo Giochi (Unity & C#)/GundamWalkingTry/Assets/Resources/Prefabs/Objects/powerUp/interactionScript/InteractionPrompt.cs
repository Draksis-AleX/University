using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class InteractionPrompt : MonoBehaviour
{
    private Camera _mainCamera;
    [SerializeField] private GameObject _uiPanel;
    [SerializeField] private TextMeshProUGUI _promptText;

    private void Start()
    {
        _mainCamera = Camera.main;
        _uiPanel.SetActive(false);
    }

    private void Update()
    {
        var rotation = _mainCamera.transform.rotation;
        transform.LookAt(transform.position + rotation * Vector3.forward, rotation * Vector3.up);
    }

    public bool IsDisplayed = false;

    public void SetUp(string promptText) {

        _promptText.text = promptText;
        _uiPanel.SetActive(true);
        IsDisplayed = true;
        
    }

    public void close() {
        _uiPanel.SetActive(false);
        IsDisplayed = false;
    }
}
