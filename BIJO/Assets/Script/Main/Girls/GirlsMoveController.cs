using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DG.Tweening;

public class GirlsMoveController : MonoBehaviour {

    [SerializeField] float m_speed;
    [SerializeField] float m_posX;

    [SerializeField] Ease ease;

    [SerializeField] GameObject girlManagerObj;
    [SerializeField] GirlsManager girlsManager;

    private void Awake()
    {
        girlManagerObj = GameObject.Find("GirlsManager(FlipMode)");

        girlsManager = girlManagerObj.GetComponent<GirlsManager>();
    }

    // Use this for initialization
    void Start()
    {


        //****************************************************************
        // タップモード時の美女の動き
        //****************************************************************

        //float random_X, random_Y;
        //random_X = Random.Range(0f, 1f);
        //random_Y = Random.Range(0f, 1f);

        //var randomForce = new Vector2(random_X, random_Y);
        //this.gameObject.GetComponent<Rigidbody2D>().AddForce(randomForce, ForceMode2D.Force);


        //****************************************************************
        // フリックモード時の美女の動き
        //****************************************************************

        var randomSpeed = Random.Range(m_speed - 0.7f, m_speed + 0.7f);

        if (this.gameObject.transform.position.x > 0)
        {
            // 画面端から端へとそれぞれの速度で移動
            this.gameObject.transform.DOLocalMoveX(m_posX, randomSpeed)
                .SetEase(Ease.Linear)
                .OnComplete(() =>
                {
                    girlsManager.m_girlsCount--;
                    Destroy(this.gameObject);
                });
        }
        else
        {
            this.gameObject.transform.DOLocalMoveX(-m_posX, randomSpeed)
                .SetEase(Ease.Linear)
                .OnComplete(() =>
                {
                    girlsManager.m_girlsCount--;
                    Destroy(this.gameObject);
                });
        }
    }
}