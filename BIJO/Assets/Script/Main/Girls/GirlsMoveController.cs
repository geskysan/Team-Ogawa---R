using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DG.Tweening;

public class GirlsMoveController : MonoBehaviour {

    [SerializeField] float m_speed;
    [SerializeField] float m_posX;

    [SerializeField] Ease ease;
    // Use this for initialization
    void Start() {

        //float random_X, random_Y;

        //random_X = Random.Range(0f, 1f);
        //random_Y = Random.Range(0f, 1f);

        //var randomForce = new Vector2(random_X, random_Y);

        //this.gameObject.GetComponent<Rigidbody2D>().AddForce(randomForce, ForceMode2D.Force);


        if (this.gameObject.transform.position.x > 0)
            this.gameObject.transform.DOMoveX(m_posX, m_speed).SetEase(Ease.Linear);
        else
            this.gameObject.transform.DOMoveX(-m_posX, m_speed).SetEase(Ease.Linear);
    }

    private void Update()
    {

    }
}