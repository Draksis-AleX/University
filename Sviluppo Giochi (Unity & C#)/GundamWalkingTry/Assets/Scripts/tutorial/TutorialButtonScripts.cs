using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class TutorialButtonScripts : MonoBehaviour 
{
    [SerializeField] GameObject title;
    [SerializeField] GameObject des;
    [SerializeField] GameObject tutorialImage;
    [SerializeField] GameObject arrowNext;
    [SerializeField] GameObject arrowPrev;
    [SerializeField] GameObject menuToHide;
    [SerializeField] GameObject menuTutorial;

    [SerializeField] List<Sprite> Showimages;

    int index;

    private void Start()
    {
        //images = new List<Sprite>();
    }


    public void ShopButton() {

        List<Sprite> tutorialImages = new List<Sprite>();

        tutorialImages.Add(((Texture2D)Resources.Load("TutorialImage/SHOP/TutorialOutsideShop")).ConvertToSprite());
        tutorialImages.Add(((Texture2D)Resources.Load("TutorialImage/SHOP/TutorialShopMenu")).ConvertToSprite());

        string descrizione = "To open the Shop Tab interact with the Shop Station in the starting hangar pressing E \n"

                                + "If you have enough money you can buy any unlocked skill you want.This Skills are PERMANENT (Unless you start a New Game).\n\n"

                                       + "Look at the second screen for a Shop Tab description.\n";

        ShowTutorial("SHOP", descrizione , true , tutorialImages);
    }

    public void GamePlayButton()
    {
        List<Sprite> tutorialImages = new List<Sprite>();

        tutorialImages.Add(((Texture2D)Resources.Load("TutorialImage/GAMEPLAY/TutorialHUD")).ConvertToSprite());
        tutorialImages.Add(((Texture2D)Resources.Load("TutorialImage/GAMEPLAY/TutorialMove")).ConvertToSprite());
        tutorialImages.Add(((Texture2D)Resources.Load("TutorialImage/GAMEPLAY/TutorialAim")).ConvertToSprite());
        tutorialImages.Add(((Texture2D)Resources.Load("TutorialImage/GAMEPLAY/TutorialShoot")).ConvertToSprite());
        tutorialImages.Add(((Texture2D)Resources.Load("TutorialImage/GAMEPLAY/TutorialCheckpoint")).ConvertToSprite());

        string descrizione = "Your HUD is composed by:\n"
                                + "- Your Health(RED)\n- Your Shield(BLU)\n- Your Coins\n\n" +

                                "To Move the Player use the WASD keys(you can switch to arrow keys in control settings)\n\n" +

                                "To aim hold the Right Button of the Mouse\n\n" +

                                "To Shoot click the Left Button of the Mouse";

        ShowTutorial("GAMEPLAY", descrizione, true, tutorialImages);
    }
    public void PUButton()
    {
        List<Sprite> tutorialImages = new List<Sprite>();

        tutorialImages.Add(((Texture2D)Resources.Load("TutorialImage/POWERUPS/TutorialOutsidePowerUps")).ConvertToSprite());
        tutorialImages.Add(((Texture2D)Resources.Load("TutorialImage/POWERUPS/TutorialPowerUPsRoom")).ConvertToSprite());

        string descrizione = "In each corridor is present a door for a PowerUP Room.\n"
                                + "You can enter in a certain PowerUP Room only ONE TIME.\n"
                                + "In these rooms you will find three PowerUPs of various rarities.\n"
                                + "You can choose only ONE oh these three PowerUPs.\n"
                                +"These PowerUPs are effective only in the actual Run and are NOT PERMANENT.\n";

        ShowTutorial("POWERUPS", descrizione, true, tutorialImages);
    }
    public void CoinButton()
    {
        List<Sprite> tutorialImages = new List<Sprite>();

        tutorialImages.Add(((Texture2D)Resources.Load("TutorialImage/COINS/TutorialCoins")).ConvertToSprite());


        string descrizione = "Each enemy you kill drops a certain amount of coins.\n"
                            +"Use these coins in the Shop.\n"
                            +"The coins you earn are saved only after you've reached a CheckPoint in a corridor (look at the second screen).\n";
        ShowTutorial("COINS", descrizione, false, tutorialImages);
    }

    public void ScoreButton()
    {
        List<Sprite> tutorialImages = new List<Sprite>();

        tutorialImages.Add(((Texture2D)Resources.Load("TutorialImage/SCORE/TutorialScore")).ConvertToSprite());
        tutorialImages.Add(((Texture2D)Resources.Load("TutorialImage/GAMEPLAY/TutorialCheckpoint")).ConvertToSprite());


        string descrizione = "You can see your actual Run Score in the bottom-right corner of the HUD.\n"
                            +"You gain score killing enemies and completing waves.\n"
                            +"If you complete a wave faster you will gain more score.\n"
                            +"The score, as coins, is saved only reaching a CheckPoint in a corridor(look at the second screen).\n";
        ShowTutorial("SCORE", descrizione, true, tutorialImages);
    }
    public void EnemyButton()
    {
        List<Sprite> tutorialImages = new List<Sprite>();

        tutorialImages.Add(((Texture2D)Resources.Load("TutorialImage/ENEMY/TutorialEnemies")).ConvertToSprite());

        string descrizione = "There are three types of enemies in the game:\n"
                            +"-Base Aku(RED): he is the basic enemy of the game.\n"
                            +"-Bulk Aku(GREEN): he has more life then a normal aku and he inflicts more damage.\n"
                            +"- Killer Aku: he is faster then a normal aku but he inflicts less damage. (Be afraid of them)\n";
        ShowTutorial("ENEMIES", descrizione, false, tutorialImages);
    }
    public void RunHistory()
    {
        List<Sprite> tutorialImages = new List<Sprite>();

        tutorialImages.Add(((Texture2D)Resources.Load("TutorialImage/RUN/TutorialOutisdeRankingPC")).ConvertToSprite());
        tutorialImages.Add(((Texture2D)Resources.Load("TutorialImage/RUN/TutorialRankingMenu")).ConvertToSprite());

        string descrizione = "In the lower left area of the starting hangar you will find the Run Ranking PC.\n"
                                +"This PC stores the best 6 runs you have completed ordered by score.\n"
                                +"Look at the second screen for a Run Ranking Tab description \n";
        ShowTutorial("RUN RANKING", descrizione, true, tutorialImages);
    }


    public void ShowTutorial(string titleName , string descrizione , bool showArrows , List<Sprite> images) {
        title.gameObject.GetComponent<TextMeshProUGUI>().text = titleName;
        des.gameObject.GetComponent<TextMeshProUGUI>().text = descrizione;

        Showimages = images;

        index = 0;

        tutorialImage.gameObject.GetComponent<Image>().sprite = Showimages[index];

        arrowNext.gameObject.SetActive(showArrows);
        arrowPrev.gameObject.SetActive(showArrows);

        menuToHide.SetActive(false);
        menuTutorial.SetActive(true);
        
    }

    public void NextButton()
    {
        index++;
        if (index > Showimages.Count - 1) index = 0;

        Debug.Log("index : " + index);
        tutorialImage.gameObject.GetComponent<Image>().sprite = Showimages[index % Showimages.Count];
    }

    public void PrevButton()
    {
        index--;
        if (index < 0) index = Showimages.Count -1;

        Debug.Log("index : " + index);
        tutorialImage.gameObject.GetComponent<Image>().sprite = Showimages[index % Showimages.Count];
    }

}
