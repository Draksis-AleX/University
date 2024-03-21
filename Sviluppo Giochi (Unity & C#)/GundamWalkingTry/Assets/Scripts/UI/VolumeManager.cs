using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Rendering;
using UnityEngine.Rendering.Universal;

public class VolumeManager : MonoBehaviour
{

    float vignetteIntensity = 0;
    VolumeProfile vprofile;
    float currentVelocity = 0;
    [SerializeField] float smoothSpeed = 25f;

    //====================================  SINGLETON  ==========================================

    private static VolumeManager _instance;

    public static VolumeManager Instance
    {
        get
        {
            if (_instance == null)
            {
                _instance = GameObject.FindObjectOfType<VolumeManager>();
                if (_instance == null) Debug.LogError("No Volume Manager");
            }
            return _instance;
        }
    }

    private void Awake()
    {
        if (_instance == null)
        {
            _instance = this;
            GameObject.DontDestroyOnLoad(this.gameObject);
        }
        else
        {
            GameObject.Destroy(this.gameObject);
        }
    }

    private void Start()
    {
        vprofile = this.GetComponent<Volume>().profile;
    }

    private void Update()
    {
        AnimateVignette();
    }

    public void setVignetteIntensity(float value)
    {
        vignetteIntensity = value;
    }

    void AnimateVignette()
    {
        float targetVignetteValue = vignetteIntensity;
        float startVignetteValue;
        Vignette vignetteEffect;
        if (vprofile.TryGet<Vignette>(out vignetteEffect))
        {
            startVignetteValue = vignetteEffect.intensity.value;
            vignetteEffect.intensity.value = Mathf.SmoothDamp(startVignetteValue, targetVignetteValue, ref currentVelocity, smoothSpeed * Time.deltaTime);
        }
    }
    
}
