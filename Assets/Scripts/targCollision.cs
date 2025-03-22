using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class targCollision : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    void OnCollisionEnter(Collision other){
        if(other.gameObject.CompareTag("Bullet")){
            Destroy(other.gameObject); //destroy the bullet after a second
            Destroy(gameObject); //destroy target immediately
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
