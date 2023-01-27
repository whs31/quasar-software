using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AircraftMovement : MonoBehaviour
{
    public float velocity = 0; //in km/h
    [SerializeField]
    private AircraftAxesState aircraftAxes;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 forwardForce = aircraftAxes.throttle * (-transform.forward);
        GetComponent<Rigidbody>().AddForce(forwardForce);
        velocity = GetComponent<Rigidbody>().velocity.magnitude * 3.6f;
        Debug.Log(velocity + "km/h");
    }
}
