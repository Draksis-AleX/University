using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "Skills/ShieldBuff")]

public class ShieldBuff : SkillEffect
{
    [SerializeField] int amount;

    public override void Apply(GameObject target)
    {
        target.GetComponent<PlayerShieldManager>().addMaxShield(amount);
    }
}
