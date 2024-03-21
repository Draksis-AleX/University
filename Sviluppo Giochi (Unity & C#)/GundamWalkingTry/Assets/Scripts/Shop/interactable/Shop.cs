using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Shop : MonoBehaviour, IInteractable
{
    public string InteractionPrompt => "Press E";
    [SerializeField] protected GameObject panel;
    [SerializeField] protected GameObject blurPanel;

    public void Action()
    {
        OpenShop();
    }

    public void OpenShop() {

        panel.SetActive(true);
        blurPanel.GetComponent<CanvasGroup>().alpha = 1;

    }

    public bool Interact(Interactor interactor)
    {
        interactor.OpenShop(this);
        return true;
    }
}
