using System.Collections;
using UnityEngine.SceneManagement;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.AI;

public class ArenaInit : InitScene
{

    [SerializeField] GameObject PropSpawnPoints;
    [SerializeField] GameObject PropPrefab;
    [SerializeField] int activePropsCount;
    [SerializeField] NavMeshSurface navSurface;

    private new void Start()
    {
        base.Start();

        if (PropSpawnPoints != null)
        {
            SpawnProps();
            navSurface.BuildNavMesh();
        }

        GameManager.Instance.EnteredArena();

    }

    void SpawnProps()
    {
        int propSP_c = PropSpawnPoints.transform.childCount;
        //Debug.Log("PropsSP Counter: " + propSP_c);

        bool[] propStatus = new bool[propSP_c];
        int propID = 0;
        for (int i = 0; i < activePropsCount; i++)
        {
            do
            {
                propID = Random.Range(0, propSP_c);
            } while (propStatus[propID] == true);
            propStatus[propID] = true;
            //Debug.Log("PropSpawnPoint : " + propID);
            int random_rotation = Random.Range(0, 8);
            Vector3 rotation = PropPrefab.transform.rotation.eulerAngles;
            rotation.y = 45 * random_rotation;
            Instantiate(PropPrefab, PropSpawnPoints.transform.GetChild(propID).transform.position, Quaternion.Euler(rotation));
        }
    }

}
