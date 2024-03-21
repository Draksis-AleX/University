using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class ShopManager : MonoBehaviour
{

    [SerializeField] TextMeshProUGUI title;
    [SerializeField] TextMeshProUGUI description;
    [SerializeField] TextMeshProUGUI price;
    [SerializeField] TextMeshProUGUI myCoins;
    [SerializeField] Skill currentSkill;
    GameObject currentSkillGO;
    GameObject lastSkillGO;
    [SerializeField] List<int> ownedSkills;

    [SerializeField] GameObject shieldTree;
    [SerializeField] GameObject healthTree;
    [SerializeField] GameObject bulletTree;

    [SerializeField] SaveUI savingUI;

    private void OnEnable()
    {
        updateMyCoins();
    }

    private void Start()
    {
        updateMyCoins();
        loadAll();
        savingUI = GameObject.Find("SavePanel").GetComponent<SaveUI>();
    }

    public void updateDescription(GameObject invoker)
    {
        //Debug.Log("updateDescription");

        currentSkillGO = invoker;
        if (lastSkillGO != null) { 
            if(lastSkillGO.GetComponent<Image>().color != Color.white) updateSkillColor(lastSkillGO, Color.black);
            //Debug.Log(lastSkillGO.ToString());
        }
        
        lastSkillGO = currentSkillGO;
        currentSkill = invoker.transform.parent.gameObject.GetComponent<Skill>();

        Color selectColor;
        if (CoinManager.Instance.getCoins() >= currentSkill.getCost()) selectColor = new Color(0, 1, 1);
        else selectColor = new Color(1f, 0, 0.2156863f);
        if(currentSkillGO.GetComponent<Image>().color != Color.white) updateSkillColor(currentSkillGO, selectColor);

        title.text = currentSkill.getTitle();
        description.text = currentSkill.getDescription();
        price.text = currentSkill.getCost().ToString();
    }

    public void updateMyCoins()
    {
        myCoins.text = CoinManager.Instance.getCoins().ToString();
    }

    public void Buy()
    {
        if(currentSkill != null)
        {
            //Debug.Log("Try Buy - Skill ID:" + currentSkill.getId());
            //--------------- Check if skill is unlocked ------------------------
            bool unlocked = false;
            if(currentSkill.getConnectedSkills().Length == 0)
            {
                unlocked = true;
            }
            else
            {
                foreach (int skillID in currentSkill.getConnectedSkills())
                {
                    if (ownedSkills.Contains(skillID))
                    {
                        unlocked = true;
                        break;
                    }
                }
            }

            //---------------- Check if alternative skill is already bought ---------------------------

            bool alternativeBought = false;
            if (currentSkill.getAlternativeSkill() != -1 && ownedSkills.Contains(currentSkill.getAlternativeSkill())) alternativeBought = true;
            else alternativeBought = false;

            //-------------------- Buy ----------------------------------------------

            if (CoinManager.Instance.getCoins() >= currentSkill.getCost() && unlocked && !currentSkill.isOwned() && !alternativeBought && (!ownedSkills.Contains(currentSkill.getId())))
            {
                AudioMenager.Instance.PlayEffect("Buy");
                Debug.Log("Skill Bought - Skill ID:" + currentSkill.getId());
                currentSkill.getSkillEffect().Apply(PlayerManager.Instance.gameObject);
                ownedSkills.Add(currentSkill.getId());
                currentSkill.setOwned(true);
                updateSkillColor(currentSkillGO, Color.white);
                CoinManager.Instance.pay(currentSkill.getCost());
                updateMyCoins();
                save();
            }
            else AudioMenager.Instance.PlayEffect("BuyError");
        }
    }

    void updateSkillColor(GameObject target, Color color)
    {
        target.GetComponent<Image>().color = color;
    }

    private void loadAll()
    {

        ShopData d = new ShopData();

        if (d.loadData("shop") != null)
        {
            d = JsonUtility.FromJson<ShopData>(d.loadData("shop"));
            ownedSkills = d.ownedSkills;
            colorOwned();
        }

    }

    private void colorOwned()
    {

        int n_skill = 8;

        Transform shieldSkills = shieldTree.gameObject.transform.GetChild(1);
        Transform healthSkills = healthTree.gameObject.transform.GetChild(1);
        Transform bulletSkills = bulletTree.gameObject.transform.GetChild(1);

        GameObject skill;

        for (int j = 0; j < ownedSkills.Capacity; j++) { 
            for (int i = 0; i < n_skill; i++)
            {

                if (ownedSkills[j] >= 0 && ownedSkills[j] <= 7)
                {
                    skill = shieldSkills.transform.GetChild(i).gameObject;

                    if (skill.gameObject.GetComponent<Skill>().getId() == ownedSkills[j])
                        skill.transform.GetChild(2).gameObject.GetComponent<Image>().color = Color.white;

                }
                else if (ownedSkills[j] >= 10 && ownedSkills[j] <= 17)
                {
                    skill = healthSkills.transform.GetChild(i).gameObject;

                    if (skill.gameObject.GetComponent<Skill>().getId() == ownedSkills[j])
                        skill.transform.GetChild(2).gameObject.GetComponent<Image>().color = Color.white;

                }
                else {

                    skill = bulletSkills.transform.GetChild(i).gameObject;

                    if (skill.gameObject.GetComponent<Skill>().getId() == ownedSkills[j])
                        skill.transform.GetChild(2).gameObject.GetComponent<Image>().color = Color.white;
                }
            }
        }


    }

    private void save()
    {
        ShopData d = new ShopData();
        d.ownedSkills  = ownedSkills;
        d.saveData("shop");
        savingUI.Show();
    }

    private void resetSave()  //per debug
    {
        ShopData d = new ShopData();
        d.saveData("shop");
    }

}


