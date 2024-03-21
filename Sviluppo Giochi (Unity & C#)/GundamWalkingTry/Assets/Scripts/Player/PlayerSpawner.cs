using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PlayerSpawner : MonoBehaviour
{

    [SerializeField] Transform spawnPoint;
    [SerializeField] Transform spawnPointMagazzino;
    private Transform sp;

    private void Start()
    {
        Respawn();
    }

    public void Respawn()
    {
        PlayerManager.Instance.GetComponent<CharacterController>().enabled = false;
        if (GameManager.Instance.gameData.inMagazzino == true) sp = spawnPointMagazzino;
        else sp = spawnPoint;

        PlayerManager.Instance.transform.position = sp.position;
        PlayerManager.Instance.transform.rotation = sp.rotation;
        //Debug.Log("Player position: " + PlayerManager.Instance.transform.position);
        if (SceneManager.GetActiveScene().name != "Magazzino")
            GameManager.Instance.gameData.inMagazzino = false;
        PlayerManager.Instance.GetComponent<CharacterController>().enabled = true;
    }

}
