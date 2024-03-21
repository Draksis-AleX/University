using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "Skills/ReducedShieldCooldown")]

public class ReducedShieldCooldown : SkillEffect
{
    [SerializeField] float percentage;

    public override void Apply(GameObject target)
    {
        target.GetComponent<PlayerShieldManager>().reduceCooldownTime(percentage);
    }
}
