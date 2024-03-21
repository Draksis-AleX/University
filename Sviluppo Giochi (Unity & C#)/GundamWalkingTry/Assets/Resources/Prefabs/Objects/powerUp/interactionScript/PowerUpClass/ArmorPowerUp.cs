using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ArmorPowerUp : PowerUp
{

    private void Start()
    {
        titlePowerUp = "ARMOR BONUS";
        infoPowerUp = "Hai trovato un PowerUp della corazza, ora potrai supire più danni senza che la tua vita diminuisca.";
        iconaPowerUp = Resources.Load<Sprite>("Image/armor-sprite");
    }

    override public void SetPowerUp() {
        SetPanel("Armor");
        PlayerManager.Instance.GetComponent<PlayerShieldManager>().addBonusShield(value);
    }
}
