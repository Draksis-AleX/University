using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "Skills/HealthPUBuff")]

public class HealthPUBuff : SkillEffect
{
    [SerializeField] float multiplier;

    public override void Apply(GameObject target)
    {
        target.GetComponent<PlayerHealthManager>().setPUMultiplier(multiplier);
    }
}
