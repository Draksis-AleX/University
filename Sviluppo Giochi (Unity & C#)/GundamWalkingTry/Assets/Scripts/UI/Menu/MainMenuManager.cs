using System.Collections;
using System.IO;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MainMenuManager : MonoBehaviour
{
    [SerializeField] string sceneName;

    public void PlayGame(){

        GameData d  = new GameData();
        GameManager.Instance.loadData = true;

        if (d.loadData("game") == null) {
            SceneManager.LoadScene(sceneName);
        }
        else {
            d = JsonUtility.FromJson<GameData>(d.loadData("game"));
            SceneManager.LoadScene(d.scene);
        }
        WindowManager.Instance.setDiplayEmpty(true);
    }

    public void Quitgame(){
        Application.Quit();
    }

    public void NewGame()
    {
        GameManager.Instance.loadData = true;
        string path = Application.persistentDataPath;
        if (Directory.Exists(path)) {

            DirectoryInfo directory = new DirectoryInfo(path);
            foreach (FileInfo file in directory.GetFiles()) {
                if (file.Name != "Player.log") file.Delete();
            }
            RankingManager.Instance.reset();
            GameManager.Instance.localData = false;
        }
        
        Directory.CreateDirectory(path);

        
        SceneManager.LoadScene(sceneName);
        WindowManager.Instance.setDiplayEmpty(true);

    }

}
