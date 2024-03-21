using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "Skills/LightWeigthShield")]

public class LightWeightShield : SkillEffect
{
    [SerializeField] float percentage;

    public override void Apply(GameObject target)
    {
        target.GetComponent<PlayerController>().increaseDefaultSpeed(percentage);
    }
}
