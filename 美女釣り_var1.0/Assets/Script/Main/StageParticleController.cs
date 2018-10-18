using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StageParticleController : MonoBehaviour {

    [SerializeField] ParticleSystem particle;

	// Use this for initialization
	void Start () {
        Instantiate(particle);
        particle.Play();
	}
}
