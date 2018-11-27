using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LureController : MonoBehaviour {

    [SerializeField] StartUpManager m_startUpManager;
    [SerializeField] GameObject m_lureObj;

    // タップ座標
    private Vector2 m_tapPos, m_touchStartPos, m_touchEndPos;
    private Vector2 m_flick;
    [SerializeField] float m_flickPower;

    private void Start()
    {
        m_flick = new Vector2(1, 1);
    }

    // Update is called once per frame
    void Update () {
        if (m_startUpManager.m_OK)
            //Tap();
            Flip();
    }


    /// <summary>
    /// タップした位置に移動
    /// </summary>
    void Tap()
    {
        if(Input.GetMouseButtonDown(0))
        {
            // 非表示状態なら表示
            if(m_lureObj.activeSelf == false)
            {
                m_lureObj.SetActive(true);
            }

            // タップした位置
            m_tapPos = new Vector2(Input.mousePosition.x, Input.mousePosition.y);

            // Lureの位置をクリック地点に移動
            m_lureObj.transform.localPosition = new Vector3(m_tapPos.x - (Screen.width / 2), m_tapPos.y - (Screen.height / 2), 0f);
        }
    }

    /// <summary>
    /// フリップした座標の取得
    /// </summary>
    void  Flip()
    {
        if(Input.GetKeyDown(KeyCode.Mouse0))
        {
            m_touchStartPos = new Vector3(Input.mousePosition.x,
                                          Input.mousePosition.y,
                                          Input.mousePosition.z);
        }

        if (Input.GetKeyUp(KeyCode.Mouse0))
        {
            m_touchEndPos = new Vector3(Input.mousePosition.x,
                                          Input.mousePosition.y,
                                          Input.mousePosition.z);
        }
    }

    /// <summary>
    /// フリックした方向を取得
    /// </summary>
    void GetDirection()
    {
        float directionX = m_touchEndPos.x - m_touchStartPos.x;
        float directionY = m_touchEndPos.y - m_touchStartPos.y;

        string Direction = "null";

        if (Mathf.Abs(directionY) < Mathf.Abs(directionX))
        {
            if (30 < directionX)
            {
                // 右側にフリック
                Direction = "right";
            }
            else if (30 > directionX)
            {
                // 左側にフリック
                Direction = "left";
            }
        }
        else if (Mathf.Abs(directionX) < Mathf.Abs(directionY))
        {
            if (30 < directionY)
            {
                Direction = "up";
            }
            else if (30 > directionY)
            {
                Direction = "down";
            }
        }
        else
        {
            // タッチを検出
            Direction = "touch";
        }

        // それぞれの方向の処理を入れる
        switch(Direction)
        {
            case "up":
                this.gameObject.GetComponent<Rigidbody2D>().AddForce(m_flick * m_flickPower);
                break;

            case "down":
                this.gameObject.GetComponent<Rigidbody2D>().AddForce(m_flick * m_flickPower);
                break;

            case "right":
                this.gameObject.GetComponent<Rigidbody2D>().AddForce(m_flick * m_flickPower);
                break;

            case "left":
                this.gameObject.GetComponent<Rigidbody2D>().AddForce(m_flick * m_flickPower);
                break;

            case "touch":
                this.gameObject.GetComponent<Rigidbody2D>().AddForce(m_flick * m_flickPower);
                break;
        }
    }
}