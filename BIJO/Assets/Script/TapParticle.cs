using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TapParticle : MonoBehaviour {

    [SerializeField,TooltipAttribute("Particle")]
    private ParticleSystem particle;

	void Update () {
        if (Input.GetMouseButtonDown(0))
        {
            var pos = Camera.main.ScreenToWorldPoint(Input.mousePosition + Camera.main.transform.forward * 10);
            particle.transform.position = pos;
            particle.Emit(1);
        }
    }
}
