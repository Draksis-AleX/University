using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

[System.Serializable]
public class ShieldData : ASave
{
     public int maxShield;
     public int bonusShield;
     public float shieldCooldownTime;
     public float regenerationTime;

    public ShieldData() { }

}