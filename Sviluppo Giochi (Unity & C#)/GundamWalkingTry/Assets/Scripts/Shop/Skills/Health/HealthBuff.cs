using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "Skills/HealthBuff")]

public class HealthBuff : SkillEffect
{
    [SerializeField] int amount;

    public override void Apply(GameObject target)
    {
        target.GetComponent<PlayerHealthManager>().addMaxHealth(amount);
    }
}
