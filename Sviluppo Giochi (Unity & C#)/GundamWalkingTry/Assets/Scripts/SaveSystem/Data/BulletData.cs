using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

[System.Serializable]
public class BulletData : ASave
{

    public float bulletForce;
    public float coolDown;

    public int playerDamage;
    public int playerCurrentDamage;
    public float vampirismPercentage;

    public BulletData() { }

}