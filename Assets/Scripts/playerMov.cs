using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class playerMov : MonoBehaviour
{
    public Transform eyes;
    public CharacterController character;
    public float currentPos = 0.0f;
    public float mouseSens = 3.5f;
    public float pace = 2.0f;
    // Start is called before the first frame update
    void Start()
    {
        character = GetComponent<CharacterController>();
        eyes = GameObject.Find("Main Camera").transform;
        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = false;
        
    }

    // Update is called once per frame
    void Update()
    {
        if(Input.GetKey(KeyCode.UpArrow)){
            character.Move(new Vector3(0.0f, 0.0f, -4.0f * Time.deltaTime));
        }
        if(Input.GetKey(KeyCode.DownArrow)){
            character.Move(new Vector3(0.0f, 0.0f, 4.0f * Time.deltaTime));
        }
        if(Input.GetKey(KeyCode.RightArrow)){
            character.Move(new Vector3(-4.0f * Time.deltaTime, 0.0f, 0.0f));
        }
        if(Input.GetKey(KeyCode.LeftArrow)){
            character.Move(new Vector3(4.0f * Time.deltaTime, 0.0f, 0.0f));
        }

        Vector2 mouseMovement = new Vector2(Input.GetAxis("Mouse X"), Input.GetAxis("Mouse Y"));
        currentPos = currentPos - mouseMovement.y;
        if(currentPos > 90.0){
            currentPos = 90.0f;
        } else if (currentPos < -90.0){
            currentPos = -90.0f;
        }
        eyes.localEulerAngles = currentPos * Vector3.right * mouseSens;
        transform.Rotate(mouseMovement.x * Vector3.up * mouseSens);

        Vector3 cameraForward = eyes.forward;
        Vector3 cameraRight = eyes.right;
        Vector2 direction = new Vector2(Input.GetAxisRaw("Horizontal"), Input.GetAxisRaw("Vertical"));
        //Vector3 movement = new Vector3(direction.x * pace, 0, direction.y * pace);
        cameraForward = cameraForward * direction.y;
        cameraRight = cameraRight * direction.x;
        Vector3 movement = cameraForward + cameraRight;
        character.Move(movement * Time.deltaTime);

        
    }
}
