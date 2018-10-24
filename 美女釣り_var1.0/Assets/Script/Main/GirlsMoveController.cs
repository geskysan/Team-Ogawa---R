using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GirlsMoveController : MonoBehaviour {

    [SerializeField] float m_speed;

    // Use this for initialization
    void Start() {

        float random_X, random_Y;

        random_X = Random.Range(0f, 1f);
        random_Y = Random.Range(0f, 1f);

        var randomForce = new Vector2(random_X, random_Y);

        this.gameObject.GetComponent<Rigidbody2D>().AddForce(randomForce, ForceMode2D.Force);
    }

	// Update is called once per frame
	void Update () {

    }

    private void OnCollisionStay2D(Collision2D collision)
    {

    }
}