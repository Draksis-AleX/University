using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShopWindow : Window
{
    [SerializeField] public GameObject blur;

    override public void other()
    {
        blur.GetComponent<CanvasGroup>().alpha = 0;
    }
}

