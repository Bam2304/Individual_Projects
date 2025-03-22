using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class targetBehavior : MonoBehaviour
{
    public GameObject target;
    public float spawnInterval = 5.0f; //spawn new target every 5 seconds
    public Vector2 rangeX = new Vector2(-17, 17); //range of x position
    public Vector2 rangeZ = new Vector2(-21, -28); //range of z position
    public float spawnHeight = 3.5f;
    // Start is called before the first frame update
    void Start()
    {
        InvokeRepeating("spawnTarget", 0f, spawnInterval); //calls spwanTarget() every 5 seconds
    }

    void spawnTarget()
    {
        Vector3 spawnPosition = new Vector3(Random.Range(rangeX.x, rangeX.y), spawnHeight,  Random.Range(rangeZ.x, rangeZ.y));
        Instantiate(target, spawnPosition, Quaternion.identity);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
