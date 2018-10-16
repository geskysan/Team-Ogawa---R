using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LureController : MonoBehaviour {

    [SerializeField]
    GameObject m_lureObj;

    // タップ時の開始座標
    private Vector2 m_startTapPos;
    // 指を離した時の座標
    private Vector2 m_endTapPos;

    // Use this for initialization
    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {

    }

    void Flick()
    {
        if (Input.GetKeyDown(KeyCode.Mouse0))
        {
            m_startTapPos = new Vector3(Input.mousePosition.x, Input.mousePosition.y);
        }

        if (Input.GetKeyUp(KeyCode.Mouse0))
        {
            m_endTapPos = new Vector3(Input.mousePosition.x, Input.mousePosition.y);
        }

        GetDirection();
    }

    void GetDirection()
    {
        float directionX = m_endTapPos.x - m_startTapPos.x;
        float directionY = m_endTapPos.y - m_startTapPos.y;

        if(Mathf.Abs(directionY) < Mathf.Abs(directionX))
        {
            if(30 < directionX)
            {
                // 右にフリック
            }
            else if(-30 > directionX)
            {
                // 左にフリック
            }
        }
        else if(Mathf.Abs(directionX) <Mathf.Abs(directionY))
        {
            if(30 < directionY)
            {
                // 上にフリック
            }
            else if(-30 >directionY)
            {
                // 下にフリック
            }

        }
    }
}
