using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class EnemyNavMeshMovement : MonoBehaviour
{

    Vector3 playerPosition;
    public NavMeshAgent agent;
    [SerializeField] Animator animator;
    public bool triggered;
    [SerializeField] int minDistance = 100;
    [SerializeField] float updateRate = 0.1f;
    public bool isAttacking;

    private const string isWalking = "isWalking"; 

    private void Start()
    {
        isAttacking = false;
        triggered = false;
        agent.avoidancePriority = Random.Range(0, 100);
    }

    private void Update()
    {

        if (!triggered) checkDistance();
        animator.SetBool(isWalking, agent.velocity.magnitude > 0.01f);
    }

    void checkDistance()
    {
        playerPosition = PlayerManager.Instance.gameObject.transform.GetChild(0).transform.position;
        float distance = Vector3.Distance(playerPosition, transform.position);
        //Debug.Log("Distance: " + distance);
        if (distance <= minDistance) 
        {
            triggered = true;
            StartCoroutine(FollowPlayer());
        }
        
    }

    private IEnumerator FollowPlayer()
    {
        yield return new WaitForSeconds(1);

        WaitForSeconds Wait = new WaitForSeconds(updateRate);

        while (enabled)
        {
            if (!isAttacking)
            {
                playerPosition = PlayerManager.Instance.gameObject.transform.GetChild(0).transform.position;
                Vector3 destination = playerPosition - (playerPosition - transform.position).normalized * 0.5f;
                //Debug.Log(this.gameObject.name.ToString() + " :: " + destination);
                agent.SetDestination(destination);
            }
            yield return Wait;
        }
    }
}