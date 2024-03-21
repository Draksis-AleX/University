using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class EnemyMovement : MonoBehaviour
{

    [SerializeField] GameObject player;
    [SerializeField] NavMeshAgent agent;

    private void Start()
    {
        agent.SetDestination(player.transform.position);
    }

}
