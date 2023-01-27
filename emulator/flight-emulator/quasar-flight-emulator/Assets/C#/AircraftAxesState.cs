
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AircraftAxesState : MonoBehaviour
{
    [Header("Axes values")]
    public float pitch = 0;
    public float yaw = 0;
    public float roll = 0;
    public float throttle = 0;

    [Header("Axes deltas")]
    public float delta_pitch = 0;
    public float delta_yaw = 0;
    public float delta_roll = 0;
    public float delta_throttle = 0;

    [Space(10)]
    [SerializeField]
    private GameObject uav = null;
    [SerializeField]
    private Transform rudder = null;
    [SerializeField]
    private Transform elevator = null;
    [SerializeField]
    private Transform rotor = null;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
