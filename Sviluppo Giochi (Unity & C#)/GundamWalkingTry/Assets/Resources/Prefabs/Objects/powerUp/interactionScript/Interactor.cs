using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;


public class Interactor : MonoBehaviour
{
    [SerializeField] private Transform _interactionPoint;
    [SerializeField] private float _interactionPointRadius = 0.8f;
    [SerializeField] private LayerMask _interactableMask;
    [SerializeField] private InteractionPrompt _InteractionPrompt;

    //private List<IInteractable> inventory = new List<IInteractable>();

    private readonly Collider[] _colliders = new Collider[3];

    [SerializeField] private int _numFound;

    private IInteractable _interactable;

    private void Update()
    {
        _numFound = Physics.OverlapSphereNonAlloc(_interactionPoint.position, _interactionPointRadius, _colliders, _interactableMask);

        if (_numFound > 0)
        {

            _interactable = _colliders[0].GetComponent<IInteractable>();

            if (_interactable != null)
            {

                if (!_InteractionPrompt.IsDisplayed) _InteractionPrompt.SetUp(_interactable.InteractionPrompt);
                if (Keyboard.current.eKey.wasPressedThisFrame) _interactable.Interact(this);

            }
        }
        else {

            if (_interactable != null) _interactable = null;
            if (_InteractionPrompt.IsDisplayed) _InteractionPrompt.close();
           
        }
    }

    private void OnDrawGizmos()
    {
        Gizmos.color = Color.red;
        Gizmos.DrawWireSphere(_interactionPoint.position, _interactionPointRadius);
    }

    public void takePowerUp(PowerUp powerUp){  
        powerUp.Action();   
        
    }

    public void OpenShop(Shop _shop) {
        _shop.Action();
    }

    public void OpenRankingPanel(RankingPC _rankingPanel)
    {
        _rankingPanel.Action();
    }
}