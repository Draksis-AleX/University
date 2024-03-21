using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "Skills/DamageIgnore")]

public class DamageIgnore : SkillEffect
{
    [SerializeField] int probability;

    public override void Apply(GameObject target)
    {
        target.GetComponent<PlayerHealthManager>().setDIProbability(probability);
    }
}

