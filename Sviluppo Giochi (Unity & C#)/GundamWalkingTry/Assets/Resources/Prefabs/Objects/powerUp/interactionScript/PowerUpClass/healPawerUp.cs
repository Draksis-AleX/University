using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class healPawerUp : PowerUp
{

 
    private void Start()
    {
        titlePowerUp = "HEAL BONUS";
        infoPowerUp = "Hai trovato un PowerUp della salute, ora potrai subire più danni.";
        iconaPowerUp = Resources.Load<Sprite>("Image/heal-sprite");
    }

    override public void SetPowerUp() {
        
        int bonusPer = (int)((float)PlayerManager.Instance.GetComponent<PlayerHealthManager>().getDefaultHealth() * (float)(value/100f));
        //Debug.Log("value:" + value + "vita: " + PlayerManager.Instance.GetComponent<PlayerHealthManager>().getDefaultHealth() + " bonus ottenuto : " + bonusPer);
        value = bonusPer;

        SetPanel("HP");
        PlayerManager.Instance.GetComponent<PlayerHealthManager>().heal(value);
    }

    

}
