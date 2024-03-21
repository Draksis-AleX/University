using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HealthBar : MonoBehaviour
{
    [SerializeField] Slider healtSlider;
    float currentVelocity = 0;
    int currentHealth;
    [SerializeField] float smoothSpeed = 25f;

    public void setHealth(int health)
    {
        currentHealth = health;
    }

    public void setMaxHealth(int health)
    {
        healtSlider.maxValue = health;
        healtSlider.value = health;
        currentHealth = health;
    }

    private void Update()
    {
        AnimateHealthBar();
    }

    void AnimateHealthBar()
    {
        float targetHealth = currentHealth;
        float startHealth = healtSlider.value;

        healtSlider.value = Mathf.SmoothDamp(startHealth, targetHealth, ref currentVelocity, smoothSpeed * Time.deltaTime);
    }
}
