using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CoinDespawn : MonoBehaviour
{
    GameObject trail;
    [SerializeField] float despawnTime = 60f;
    public int nextScene = 2;

    private void Awake()
    {
        trail = transform.GetChild(0).gameObject;
    }

    private void Start()
    {
        despawnTime += Random.Range(-2f, +2f);
        StartCoroutine(despawn());
    }

    private IEnumerator despawn()
    {
        yield return new WaitForSeconds(despawnTime);
        Destroy(transform.parent.gameObject);
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            AudioMenager.Instance.PlayEffect("CoinPick");
            CoinManager.Instance.addCoins(1);
            Destroy(transform.parent.gameObject);
        }
    }

    private void OnDestroy()
    {
        if (!this.gameObject.scene.isLoaded) return;
        trail.transform.parent = null;
        trail.GetComponent<TrailRenderer>().autodestruct = true;
        trail = null;
    }
}
