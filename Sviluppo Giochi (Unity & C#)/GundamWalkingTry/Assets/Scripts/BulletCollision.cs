using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletCollision : MonoBehaviour
{

    [SerializeField] GameObject fireParticlePrefab;

    private void OnTriggerEnter(Collider other)
    {
        Instantiate(fireParticlePrefab, this.transform.position, this.transform.rotation);
        this.gameObject.SetActive(false);
        this.gameObject.GetComponent<Rigidbody>().velocity = Vector3.zero;
        this.gameObject.GetComponent<Rigidbody>().angularVelocity = Vector3.zero;

        if (other.CompareTag("Enemy"))
        {
            Shooting playerShooting = PlayerManager.Instance.GetComponent<Shooting>();
            other.gameObject.GetComponent<EnemyHealth>().takeDamage(playerShooting.getDamage());
            if(playerShooting.getVampirismPercentage() > 0)
            {
                int amount = Mathf.CeilToInt((float)playerShooting.getDamage() * playerShooting.getVampirismPercentage());
                PlayerManager.Instance.GetComponent<PlayerHealthManager>().heal(amount);
            }
        }
    }

}
