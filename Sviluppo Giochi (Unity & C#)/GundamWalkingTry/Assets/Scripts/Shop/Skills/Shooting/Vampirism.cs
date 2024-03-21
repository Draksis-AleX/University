using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "Skills/Vampirism")]

public class Vampirism : SkillEffect
{
    [SerializeField] float percentage;

    public override void Apply(GameObject target)
    {
        target.GetComponent<Shooting>().addVampirismPercentage(percentage);
    }
}
