using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

[System.Serializable]
public class HealthData : ASave
{
    public int defaultHealth ;
    public float PU_effect_multiplier;
    public int damageIgnoreProbability;
    public int currentHealth;

    public HealthData() {}

}
