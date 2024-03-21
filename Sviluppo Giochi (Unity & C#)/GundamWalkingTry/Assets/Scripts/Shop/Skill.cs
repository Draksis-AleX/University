using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Skill : MonoBehaviour
{
    [SerializeField] int id;
    [SerializeField] string title;
    [SerializeField] string description;
    [SerializeField] int cost;
    [SerializeField] int[] connected_skills;
    [SerializeField] bool owned;
    [SerializeField] SkillEffect effect;
    [SerializeField] int alternativeSkill = -1;

    public Skill(int id, string title, string description, int cost, int skillType, int skillEffect, int skillEffectValue)
    {
        this.id = id;
        this.title = title;
        this.description = description;
        this.cost = cost;
    }

    public int getId() { return this.id; }
    public string getTitle() { return this.title; }
    public string getDescription() { return this.description; }
    public int getCost() { return this.cost; }
    public int[] getConnectedSkills() { return this.connected_skills;  }
    public int getAlternativeSkill() { return alternativeSkill; }
    public SkillEffect getSkillEffect() { return this.effect; }
    public bool isOwned() { return owned; }

    public void setOwned(bool tf) { this.owned = tf; }
}
