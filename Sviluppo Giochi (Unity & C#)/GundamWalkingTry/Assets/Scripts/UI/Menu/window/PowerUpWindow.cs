using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PowerUpWindow : Window
{
    [SerializeField] public GameObject blur;

    override public void other() {
        blur.SetActive(false);
    }
}
