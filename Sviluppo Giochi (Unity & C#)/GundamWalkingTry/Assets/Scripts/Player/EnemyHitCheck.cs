using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class EnemyHitCheck : MonoBehaviour
{
    bool isColliding = false;

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            isColliding = true;
        }
    }
    private void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            isColliding = false;
        }
    }

    public bool checkHit()
    {
        if (isColliding)
        {
            //Debug.Log("Player Hitted");
            return true;
        }
        else return false;
    }
}
