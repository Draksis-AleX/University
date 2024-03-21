using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ShieldBar : MonoBehaviour
{
    [SerializeField] Slider shieldSlider;
    float currentVelocity = 0;
    int currentShield;
    [SerializeField] float smoothSpeed = 25f;

    private void Awake()
    {
        Debug.Log("ShieldBarUI Awake");
    }

    public void setShield(int health)
    {
        currentShield = health;
    }

    public void setMaxShield(int health)
    {
        shieldSlider.maxValue = health;
        shieldSlider.value = health;
        currentShield = health;
    }

    private void Update()
    {
        AnimateShieldBar();
    }

    void AnimateShieldBar()
    {
        float targetHealth = currentShield;
        float startHealth = shieldSlider.value;

        shieldSlider.value = Mathf.SmoothDamp(startHealth, targetHealth, ref currentVelocity, smoothSpeed * Time.unscaledDeltaTime);
    }

}
