using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TapParticle : MonoBehaviour {

    [SerializeField,TooltipAttribute("Particle")]
    private ParticleSystem particle;

    [SerializeField, TooltipAttribute("Camera")]
    private Camera _camera;

    void Start () {

    }

	void Update () {
        if (Input.GetMouseButtonDown(0))
        {
            var pos = _camera.ScreenToWorldPoint(Input.mousePosition + _camera.transform.forward * 10);
            particle.transform.position = pos;
            particle.Emit(1);
        }
    }
}
