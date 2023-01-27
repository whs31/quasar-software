
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AircraftAxesState : MonoBehaviour
{
    [Header("Axes values")]
    [Range(-1.0f, 1.0f)]    public float pitch = 0;
    [Range(-1.0f, 1.0f)]    public float yaw = 0;
    [Range(-1.0f, 1.0f)]    public float roll = 0;
    [Range(0.01f, 1.0f)]    public float throttle = 0;

    [Header("Axes deltas")]
    [Range(-0.1f, 0.1f)]    public float delta_pitch = 0;
    [Range(-0.1f, 0.1f)]    public float delta_yaw = 0;
    [Range(-0.1f, 0.1f)]    public float delta_roll = 0;
    [Range(-0.1f, 0.1f)]    public float delta_throttle = 0.01f;

    [Space(10)]
    [SerializeField]
    private GameObject uav = null;
    [SerializeField]
    private Transform rudder = null;
    [SerializeField]
    private Transform elevator = null;
    [SerializeField]
    private Transform rotor = null;

    private Animator rotorAnimator = null;

    // Start is called before the first frame update
    void Start()
    {
        rotorAnimator = rotor.GetComponent<Animator>(); 
    }

    // Update is called once per frame
    void Update()
    {
        getInput();
        throttle = Mathf.Clamp(Mathf.Lerp(throttle, throttle + delta_throttle / 150, 1), 0.01f, 1.0f);

        applyChanges();
        log();
    }

    void getInput()
    {
        delta_pitch = Input.GetAxisRaw("Pitch") / 10 * (-1);
        delta_yaw = Input.GetAxisRaw("Yaw") / 10;
        delta_roll = Input.GetAxisRaw("Roll") / 10;
        delta_throttle = Input.GetAxisRaw("Throttle") / 10;
        if (Input.GetKeyDown(KeyCode.Z))
            StartCoroutine(maxThrottle());
        else if (Input.GetKeyDown(KeyCode.X))
            StartCoroutine(minThrottle());
    }    

    void applyChanges()
    {
        rotorAnimator.speed = throttle;

        Quaternion startRotation = elevator.rotation;
        Quaternion endRotation = Quaternion.Euler(-delta_pitch * 600, elevator.rotation.eulerAngles.y, elevator.rotation.eulerAngles.z);
        elevator.rotation = Quaternion.Lerp(startRotation, endRotation, 2 * Time.deltaTime);
    }

    void log()
    {
        Debug.Log(string.Format("Pitch: {0} | Yaw: {1} | Roll: {2} | Throttle: {3}", pitch, yaw, roll, throttle));
    }

    IEnumerator maxThrottle()
    {
        float t = 0;
        while (throttle < 0.99f)
        {
            t += 0.15f * Time.deltaTime;
            if (t >= 0.15f)
                break;
            throttle = Mathf.Clamp(Mathf.Lerp(throttle, 1, t), 0.01f, 1.0f);
            yield return null;
        }
        yield return null;
    }
    IEnumerator minThrottle()
    {
        float t = 0;
        while (throttle > 0.02f)
        {
            t += 0.15f * Time.deltaTime;
            if (t >= 0.15f)
                break;
            throttle = Mathf.Clamp(Mathf.Lerp(throttle, 0.01f, t), 0.01f, 1.0f);
            yield return null;
        }
        yield return null;
    }
}
