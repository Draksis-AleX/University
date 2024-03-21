using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TriggerDoorController : MonoBehaviour
{
    [SerializeField] private Animator upperDoor;
    [SerializeField] private Animator lowerDoor;

    private void OnTriggerEnter(Collider other)
    {
        if (this.CompareTag("PortaArena") && GameManager.Instance.gameData.completedArena == false) return;
        if (this.CompareTag("PortaMagazzino") && GameManager.Instance.gameData.tookPowerUp == true) return;
        if (other.CompareTag("Player"))
        {
            AudioMenager.Instance.PlayEffect("OpenDoor");
            upperDoor.SetBool("Open", true);
            lowerDoor.SetBool("Open", true);
            //Debug.Log("Trigger Door Enter");
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (this.CompareTag("PortaArena") && GameManager.Instance.gameData.completedArena == false) return;
        if (this.CompareTag("PortaMagazzino") && GameManager.Instance.gameData.tookPowerUp == true) return;
        if (other.CompareTag("Player"))
        {
            AudioMenager.Instance.PlayEffect("CloseDoor");
            upperDoor.SetBool("Open", false);
            lowerDoor.SetBool("Open", false);
            //Debug.Log("Trigger Door Exit");
        }        
    }

}
