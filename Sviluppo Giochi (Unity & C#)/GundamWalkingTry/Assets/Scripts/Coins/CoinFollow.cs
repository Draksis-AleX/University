using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CoinFollow : MonoBehaviour
{
    [SerializeField] Vector3 target;
    [SerializeField] Vector3 dropPoint;
    [SerializeField] float minTimeModifier;
    [SerializeField] float maxTimeModifier;
    float lootDistance = 1.5f;
    bool isFollowing = false;
    bool isDropping = false;

    Vector3 _velocity = Vector3.zero;

    void Update()
    {
        //Debug.Log("Player Distance from coin: " + Vector3.Distance(PlayerManager.Instance.transform.position, this.transform.position) + " < " + lootDistance + " -> " + (Vector3.Distance(PlayerManager.Instance.transform.position, this.transform.position) < lootDistance));
        if (Vector3.Distance(PlayerManager.Instance.transform.position, this.transform.position) < lootDistance)
        {
            //Debug.Log("StartFollowing");
            isFollowing = true;
        }

        if (isDropping && !isFollowing)
        {
            transform.position = Vector3.SmoothDamp(transform.position, dropPoint, ref _velocity, Time.deltaTime * Random.Range(minTimeModifier, maxTimeModifier));
        }
        else if (isFollowing)
        {
            transform.position = Vector3.Lerp(transform.position, PlayerManager.Instance.transform.position + new Vector3(0, 1, 0), Time.deltaTime * Random.Range(minTimeModifier, maxTimeModifier));
        }

    }

    public void dropCoins(Vector3 dropPoint)
    {
        this.dropPoint = dropPoint;
        //Debug.Log("DropPoint: " + this.dropPoint);
        this.dropPoint.y += 0.3f;
        this.dropPoint.x += Random.Range(-2f, 2f);
        this.dropPoint.z += Random.Range(-2f, 2f);
        //Debug.Log("DropPointRandom: " + this.dropPoint);
        isDropping = true;
    }
}
