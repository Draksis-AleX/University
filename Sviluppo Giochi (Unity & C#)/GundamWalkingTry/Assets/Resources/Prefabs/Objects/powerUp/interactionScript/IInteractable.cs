using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public interface IInteractable 
{
    string InteractionPrompt { get;}

    public bool Interact(Interactor interactor);
    public void Action();
}
