using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class shoot : MonoBehaviour
{
    // Start is called before the first frame update
    public GameObject barrel;
    public GameObject camera2;
    public GameObject bullet;
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(UnityEngine.Input.GetMouseButtonDown(0)){
            GameObject newBullet = Instantiate(bullet, barrel.transform.position, barrel.transform.rotation); //make new bullet with same position as barrel
            newBullet.GetComponent<Rigidbody>().AddForce(transform.up * 1000); //give it a force of 1000 and send it forward

        }

    }
}
