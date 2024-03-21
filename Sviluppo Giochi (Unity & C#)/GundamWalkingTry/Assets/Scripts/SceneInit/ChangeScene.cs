using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;
using UnityEngine.InputSystem;

public class ChangeScene : MonoBehaviour
{

    [SerializeField] string sceneName;

    protected void OnTriggerEnter(Collider other)
    {
        if (this.CompareTag("PortaArena") && GameManager.Instance.gameData.completedArena == false) return;
        if (this.CompareTag("PortaMagazzino") && GameManager.Instance.gameData.tookPowerUp == true) return;
        if (other.CompareTag("Player"))
        {
            if (sceneName == "Magazzino") GameManager.Instance.gameData.inMagazzino = true;
            PlayerManager.Instance.gameObject.GetComponent<PlayerInput>().enabled = false;
            PlayerManager.Instance.gameObject.SetActive(false);
            //StartCoroutine(UnloadScene(SceneManager.GetActiveScene().buildIndex));
            if (sceneName.Length > 0) SceneManager.LoadScene(sceneName);
            else SceneManager.LoadScene(GameManager.Instance.gameData.nextScene);
        }
    }
}
