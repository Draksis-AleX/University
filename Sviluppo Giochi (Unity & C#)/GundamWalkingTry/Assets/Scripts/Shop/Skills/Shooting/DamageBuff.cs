using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "Skills/DamageBuff")]

public class DamageBuff : SkillEffect
{
    [SerializeField] int amount;

    public override void Apply(GameObject target)
    {
        target.GetComponent<Shooting>().addDamage(amount);
    }
}
