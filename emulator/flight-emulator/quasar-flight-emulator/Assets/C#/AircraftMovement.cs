using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AircraftMovement : MonoBehaviour
{
    public float velocity = 0; //in km/h
    public float torque = 1;

    [SerializeField]
    private AircraftAxesState aircraftAxes;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        GetComponent<Rigidbody>().AddTorque(transform.up * torque * aircraftAxes.yaw);
        GetComponent<Rigidbody>().AddTorque(transform.forward * torque * aircraftAxes.roll * 3);
        GetComponent<Rigidbody>().AddTorque(transform.right * torque * aircraftAxes.pitch * 2);
        moveForward();
    }

    void moveForward()
    {
        Vector3 forwardForce = aircraftAxes.throttle * 2 * (-transform.forward);
        GetComponent<Rigidbody>().AddForce(forwardForce);
        velocity = GetComponent<Rigidbody>().velocity.magnitude * 3.6f;
        Debug.Log(velocity + "km/h");
    }
}
