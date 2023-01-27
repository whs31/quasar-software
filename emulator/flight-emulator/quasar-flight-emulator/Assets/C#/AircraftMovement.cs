using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AircraftMovement : MonoBehaviour
{
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
    }
}
