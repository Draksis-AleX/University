using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "Skills/CooldownBuff")]

public class CooldownBuff : SkillEffect
{
    [SerializeField] float percentage;

    public override void Apply(GameObject target)
    {
        target.GetComponent<Shooting>().reduceCooldown(percentage);
    }
}
