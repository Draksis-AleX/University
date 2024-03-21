using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "Skills/ShieldRegenerationBuff")]

public class ShieldRegenerationBuff : SkillEffect
{
    [SerializeField] float percentage;

    public override void Apply(GameObject target)
    {
        target.GetComponent<PlayerShieldManager>().reduceRegenerationTime(percentage);
    }
}
